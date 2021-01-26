add_executable(
  unicorn
  picounicornserialdriver.cpp
)

# Pull in pico libraries that we need
target_link_libraries(unicorn pico_stdlib hardware_pio hardware_dma pico_unicorn)

pico_enable_stdio_usb(unicorn 1)
pico_enable_stdio_uart(unicorn 0)

# create map/bin/hex file etc.
pico_add_extra_outputs(unicorn)

