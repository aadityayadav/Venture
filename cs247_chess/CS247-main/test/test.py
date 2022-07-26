from io_tester import IOTester

test_runner = IOTester("final", [
    "checks_bishop",
    "checks_king",
    "checks_knight",
    "checks_pawn",
    "checks_queen",
    "checks_rook",
    "setup_all_types",
    "setup_basic",
    "setup_basic_check",
    "setup_num_kings",
    "setup_remove",
    "setup_two_same_kings"
])

test_runner.create_executable()
test_runner.run_test_suite()
