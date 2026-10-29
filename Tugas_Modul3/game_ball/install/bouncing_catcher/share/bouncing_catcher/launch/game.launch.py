from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # 1. Menjalankan Camera Node
        Node(
            package='bouncing_catcher',   # Ganti dengan nama paketmu yang sebenarnya
            executable='camera_node',     # Nama file executable kamera
            name='camera_node',
            output='screen'
        ),
        
        # 2. Menjalankan Game Node beserta Parameternya
        Node(
            package='bouncing_catcher',
            executable='game_node',       # Nama file executable game (C++)
            name='game_node',
            output='screen',
            parameters=[
                # DI SINILAH KAMU MENGATUR PARAMETER DARI LUAR C++!
                {'num_balls': 3},                  # Mengubah jumlah bola jadi 5
                {'hold_duration': 2.0},            # Mengubah waktu tahan jadi 1.5 detik
                {'ball_speed': 150.0},             # Mempercepat bola
                {'ball_radius': 50}
                # (Parameter HSV tidak ditulis di sini tidak apa-apa, 
                # dia akan otomatis pakai nilai default yang ada di C++)
            ]
        )
    ])
