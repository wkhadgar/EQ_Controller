cmake_minimum_required(VERSION 3.20.0)

set(CONFIG_BOARD "stm32_min_dev_blue")

find_package(Zephyr)
project(eq-controller)
add_link_options(--print-memory-usage,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map)

include_directories(BEFORE src)

target_sources(app PRIVATE src/main.c src/driver/rotary/rotary_events.c)