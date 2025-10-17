import pygame
import math
import serial
import time

# === Cấu hình UART ===
ser = serial.Serial(port="COM8", baudrate=9600, timeout=0)  # timeout nhỏ để tránh dữ liệu rác

# === Khởi tạo cửa sổ ===
w, h = 700, 700
pygame.init()
screen = pygame.display.set_mode((w, h))
pygame.display.set_caption("radar")

cx, cy = 350, 700
r = 350
font = pygame.font.SysFont(None, 24)

sweep_angle = 90
direction = 1
clock = pygame.time.Clock()

# lưu (x, y, timestamp)
object_points = []

# cấu hình lọc dữ liệu
MAX_DIST_CM = 300.0
MIN_VALID_DISTANCE_CM = 5       # bỏ giá trị <5cm (thường là nhiễu)
POINT_LIFETIME = 3.0
PW_MIN = 250
PW_MAX = 1250

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit()

    keys = pygame.key.get_pressed()
    if keys[pygame.K_c]:
        object_points.clear()

    # xóa chấm cũ quá hạn
    now = time.time()
    object_points = [(x, y, t) for (x, y, t) in object_points if (now - t) < POINT_LIFETIME]

    screen.fill((0, 0, 0))
    pygame.draw.circle(screen, (89, 199, 243), (cx, cy), r)

    # vạch chia 30°
    for a in range(0, 181, 30):
        rad = math.radians(a)
        x = cx + r * math.cos(rad)
        y = cy - r * math.sin(rad)
        pygame.draw.line(screen, (51, 255, 102), (cx, cy), (x, y), 1)
        tx = cx + (r + 20) * math.cos(rad)
        ty = cy - (r + 20) * math.sin(rad)
        text = font.render(f"{a}°", True, (255, 255, 0))
        screen.blit(text, (tx - 10, ty - 10))

    # tia radar
    rad = math.radians(sweep_angle)
    x = cx + r * math.cos(rad)
    y = cy - r * math.sin(rad)
    pygame.draw.line(screen, (255, 165, 0), (cx, cy), (x, y), 5)

    # === Đọc UART ===
    if ser.in_waiting > 0:
        raw_line = ser.readline().decode(errors="ignore").strip()
        if raw_line:
            parts = raw_line.split()
            if len(parts) >= 2:
                try:
                    distance = int(parts[0])
                    raw_angle = int(parts[1])
                except ValueError:
                    distance = None

                if distance is not None:
                    # lọc giá trị không hợp lệ
                    if MIN_VALID_DISTANCE_CM <= distance <= MAX_DIST_CM:
                        # tính góc (PWM hoặc trực tiếp)
                        if raw_angle > 180:
                            raw_clamped = max(min(raw_angle, PW_MAX), PW_MIN)
                            angle_deg = round((raw_clamped - PW_MIN) * 180.0 / (PW_MAX - PW_MIN))
                        else:
                            angle_deg = raw_angle

                        if 0 <= angle_deg <= 180:
                            text_data = font.render(f"distance : {distance} cm , angle : {angle_deg}°", True, (255, 255, 0))
                            screen.blit(text_data, (20, 20))

                            # chỉ vẽ chấm đỏ nếu vật nằm trong vùng gần (ví dụ < 280cm)
                            if distance < 50:
                                d_px = distance * r / MAX_DIST_CM
                                rad_t = math.radians(angle_deg)
                                target_x = cx + d_px * math.cos(rad_t)
                                target_y = cy - d_px * math.sin(rad_t)
                                object_points.append((int(target_x), int(target_y), now))
                    # nếu distance không hợp lệ -> bỏ qua
                    else:
                        pass

    # vẽ các chấm còn lại
    for (px, py, t) in object_points:
        pygame.draw.circle(screen, (255, 0, 0), (px, py), 5)

    pygame.display.update()
    clock.tick(60)

    # quay tia radar
    sweep_angle += direction * 1
    if sweep_angle >= 180:
        sweep_angle = 180
        direction = -1
    elif sweep_angle <= 0:
        sweep_angle = 0
        direction = 1
