package(default_visibility = ["//visibility:public"])

constraint_setting(
    name = "display_type",
    default_constraint_value = "${default_display_type}",
)

constraint_value(
    name = "unknown",
    constraint_setting = ":display_type",
)

constraint_value(
    name = "x11",
    constraint_setting = ":display_type",
)
