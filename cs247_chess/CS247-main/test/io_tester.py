import os, subprocess
from pathlib import Path


class IOTester:
    source_path = Path(os.path.dirname(os.path.abspath(__file__)))
    cpp_path = source_path.parent.absolute()
    test_suite_path = source_path.joinpath('suite')

    def __init__(self, executable_name: str, test_suite: list[str]):
        self.executable_name = executable_name
        self.test_suite = test_suite

    @staticmethod
    def create_executable(clean: bool = False):
        if clean:
            subprocess.call("make clean", shell=True, cwd=IOTester.cpp_path)
        subprocess.call("make", shell=True, cwd=IOTester.cpp_path)

    def run_test_suite(self):
        failed_test_count = 0
        for test in self.test_suite:
            input = ' '.join(open(IOTester.test_suite_path.joinpath(test + '.in'), 'r').read().splitlines())
            process = subprocess.run("./{}".format(self.executable_name), input=bytes(input, 'utf-8'), shell=True, cwd=IOTester.cpp_path, stdout=subprocess.PIPE)
            output = process.stdout.decode().splitlines()
            expected_output = open(IOTester.test_suite_path.joinpath(test + '.out'), 'r').read().splitlines()
            if output == expected_output:
                print("Passed test", test)
            else:
                failed_test_count += 1
                print("Failed test", test)
                print("Expected Output: ", expected_output)
                print("Actual Output: ", output)
        print("Failed {} tests".format(failed_test_count))
