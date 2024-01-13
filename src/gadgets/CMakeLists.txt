file(GLOB gadget_sources "*.cpp")
add_library(ethsnarks_gadgets STATIC ${gadget_sources})
target_link_libraries(ethsnarks_gadgets ethsnarks_common SHA3IUF)

file(GLOB gadget_headers "*.hpp")
set_target_properties(ethsnarks_gadgets PROPERTIES PUBLIC_HEADER "${gadget_headers}")
install(TARGETS ethsnarks_gadgets LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include/ethsnarks/gadgets)