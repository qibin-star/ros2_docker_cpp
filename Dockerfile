FROM ros:humble-ros-core

# 使用 bash 作为默认 shell，方便 source
SHELL ["/bin/bash", "-c"]

# 安装构建工具 + rosbridge + 第三方库
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    python3-colcon-common-extensions \
    ros-humble-rosbridge-server \
    nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

# 创建工作空间，并拷贝源码
WORKDIR /ros2_ws
RUN mkdir -p src

# 将宿主机的源代码复制进镜像（不是挂 volume）
COPY src ./src

# 在构建镜像阶段直接编译
RUN source /opt/ros/humble/setup.bash && \
    cd /ros2_ws && \
    colcon build

# 拷贝入口脚本
COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

ENTRYPOINT ["/entrypoint.sh"]
CMD ["bash"]
