
# Debugowanie biblioteki tafowej

# sandbox_runner.py
import argparse
from unittest.mock import patch

# ===============================
# Fake Robot Framework dependencies
# ===============================

class _FakeBuiltIn:
    """Minimal stub for robot.libraries.BuiltIn.BuiltIn."""

    def get_variable_value(self, name, default=None):
        overrides = {
            "${collectttitraces}": "True",
            "${test_settings}": {"collectttitraces": False, "sw_version": "softwareABC"},
        }
        return overrides.get(name, default)

    def log_to_console(self, msg, stream='stdout', no_newline=False):
        end = '' if no_newline else '\n'
        print(f"[RF-LOG] {msg}", end=end)

    def set_test_variable(self, name, value):
        print(f"[RF-SETVAR] {name} = {value}")


class _FakeConsoleLogger:
    """Stub dla logger.console wywoływanego jako funkcja."""

    def __call__(self, msg, level="INFO"):
        print(f"[RF-CONSOLE-{level}] {msg}")


class _FakeLogger:
    """Minimal stub for robot.api.logger"""

    def __init__(self):
        self.logger = self
        self.console = _FakeConsoleLogger()

    def info(self, msg, html=False):
        print(f"[RF-INFO] {msg}")

    def debug(self, msg, html=False):
        print(f"[RF-DEBUG] {msg}")

    def warn(self, msg, html=False):
        print(f"[RF-WARN] {msg}")

    def error(self, msg, html=False):
        print(f"[RF-ERROR] {msg}")

fake_logger = _FakeLogger()



# tutaj wymieniamy wartości jaką biblioteke i co tam cza
with patch("robot.libraries.BuiltIn.BuiltIn", _FakeBuiltIn), \
        patch("robot.api.logger", fake_logger):
    
    from interface import ta_dspi
    from libraries.ta_ttitrace_support import ta_ttitrace_support

    support = ta_ttitrace_support()
    choses_cores = support.choose_cores_for_tti_trace_from_given_number_of_cells_for_both_directions(num_of_cells=1) 
    dspi = ta_dspi()

    dspi.start_collecting_tti_trace_using_tti_trace_server(
        tti_trace_duration=10,
        tti_trace_cores=choses_cores,
        tti_tracer_files_dir="/home/ute/logs/tti_907_activated"
    )

    