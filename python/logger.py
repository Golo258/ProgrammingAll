import logging
from colorama import init, Fore, Style

init(autoreset=True)


class ColoredFormatter(logging.Formatter):
    LEVEL_COLORS = {
        logging.DEBUG: Fore.CYAN,
        logging.INFO: Fore.GREEN,
        logging.WARNING: Fore.YELLOW,
        logging.ERROR: Fore.RED,
        logging.CRITICAL: Fore.MAGENTA,
    }

    def format(self, record):
        color = self.LEVEL_COLORS.get(record.levelno, Fore.WHITE)
        formatted = super().format(record)
        return f"{color}{formatted}{Style.RESET_ALL}"


handler = logging.StreamHandler()
handler.setFormatter(
    ColoredFormatter("%(asctime)s [%(levelname)s] %(message)s")
)

logger = logging.getLogger()
logger.setLevel(logging.DEBUG)
logger.addHandler(handler)

if __name__ == '__main__':
    logger.info("Program started ")
    logger.warning("Its a warning ")
    logger.error("Something went wrong ")

# 

from typing import Optional
import os
import logging



class _ConsoleOptInFilter(logging.Filter):
    """
    Filters log records so only those with `to_console=True`
    (set via the `extra` dict) are shown in the console output.
    """
    def filter(self, record: logging.LogRecord) -> bool:
        """Return True only if the log record has `to_console=True`."""
        return bool(getattr(record, "to_console", False))


#-------------------
# Better one

class LoggerManager:
    """
    Singleton logger manager that auto-initializes the logger upon first use.
    """
    _logger: Optional[logging.Logger] = None
    _name: str = "auto_logger"
    _output_dir: str = "/home/user/logs"

    @classmethod
    def configure(cls, name: str, output_dir: str) -> None:
        """
        Optionally sets the logger's name and output directory before the first log is written.

        :param name: Name of the logger.
        :param output_dir: Directory to store log files.
        """
        cls._name = name
        cls._output_dir = output_dir

    @classmethod
    @property
    def logger(cls) -> logging.Logger:
        """
        Lazily creates and returns a singleton logger instance.
        """
        if cls._logger is None:
            cls._logger = logging.getLogger(f"{cls._name}_logger")
            cls._logger.setLevel(logging.DEBUG)
            cls._logger.propagate = False

            os.makedirs(cls._output_dir, exist_ok=True)

            # === FILE handler: full format with date ----
            file_format = (
                "[LISTENER]"
                "[%(asctime)s] | "
                "%(name).25s | "
                "%(levelname)-7s | "
                "%(threadName).20s | "
                "%(message)s /// "
                "%(funcName)s::%(filename)s(%(lineno)d)"
            )
            file_handler = logging.FileHandler(
                os.path.join(cls._output_dir, f"{cls._name}.log"),
                mode="a",
                encoding="utf-8",
            )
            file_handler.setLevel(logging.DEBUG)
            file_handler.setFormatter(logging.Formatter(file_format))
            cls._logger.addHandler(file_handler)

            # === CONSOLE handler: short format, only INFO with to_console=True === #
            console_format = "[LISTENER][%(levelname)s] %(message)s"
            console_handler = logging.StreamHandler()
            console_handler.setLevel(logging.INFO)  # filtr poziomu
            console_handler.setFormatter(logging.Formatter(console_format))
            console_handler.addFilter(_ConsoleOptInFilter())  # filtr 'to_console'
            cls._logger.addHandler(console_handler)

        return cls._logger

    @classmethod
    def log_msg(cls, msg: str, lvl: str = "INFO", to_console: bool = False) -> None:
        """
        Logs a message to file and optionally to Robot Framework console.

        :param msg: Message to be logged.
        :param lvl: Logging level (e.g., "INFO", "ERROR", "DEBUG").
        :param to_console: Whether to also log to Robot Framework console.
        """
        log_method = getattr(cls.logger, lvl.lower(), cls.logger.info)
        log_method(msg, extra={"to_console": to_console})

#-------------------