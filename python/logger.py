import logging
import os
from logging.handlers import RotatingFileHandler
from typing import Optional

class LoggerManager:
    """
    Singleton logger manager that auto-initializes the logger upon first use.
    """
    _logger: Optional[logging.Logger] = None
    _name: str = "default_log"  # ustawiamy domyślną nazwę
    _output_dir: str = os.path.join(os.environ.get("WORKSPACE", os.getcwd()), "UPDATE_RESULTS")

    COLORS = {
        'DEBUG': '\033[0;34m',    # blue
        'INFO': '\033[0;32m',     # green
        'WARNING': '\033[0;33m',  # yellow
        'ERROR': '\033[0;31m',    # red
        'CRITICAL': '\033[1;31m', # bold red
        'RESET': '\033[0m'
    }

    @classmethod
    def configure(cls, name: str | None = None, output_dir: str | None = None) -> None:
        """
        Configures the logger with the provided name and output directory.
        If no name is provided, defaults to 'default_log'.
        """
        if name:
            if cls._name != name:  # Jeśli nazwa się zmienia, resetujemy loggera
                cls._logger = None
            cls._name = name
        if output_dir:
            cls._output_dir = output_dir
    
        return cls.logger

    # ==== INTERNAL HELPERS ======
    @classmethod
    def _create_base_logger(cls) -> logging.Logger:
        """Create the base logger with the current name."""
        logger = logging.getLogger(cls._name)
        logger.setLevel(logging.DEBUG)  # Set to DEBUG to log everything
        logger.propagate = False
        return logger

    @classmethod
    def _add_file_handler(cls, logger: logging.Logger) -> None:
        """Handler: write to file (DEBUG+)"""
        path = os.path.join(cls._output_dir, f"{cls._name}.log")
        fmt = logging.Formatter(
            "[%(asctime)s] | %(name).25s | %(levelname)-7s | "
            "%(message)s /// %(funcName)s::%(filename)s(%(lineno)d)"
        )
        fh = RotatingFileHandler(path, mode="a", encoding="utf-8",
                                 maxBytes=10 * 1024 * 1024, backupCount=5)
        fh.setLevel(logging.DEBUG)  # Log everything to the file
        fh.setFormatter(fmt)
        logger.addHandler(fh)
    
    @staticmethod
    def _add_console_handler(logger: logging.Logger) -> None:
        """Handler: console (INFO+), with colors."""
        fmt = logging.Formatter("[%(levelname)s] %(message)s")
        ch = logging.StreamHandler()
        ch.setLevel(logging.INFO)
        ch.setFormatter(fmt)
        logger.addHandler(ch)

    @classmethod
    @property
    def logger(cls) -> logging.Logger:
        if cls._logger:
            return cls._logger
        
        logger = cls._create_base_logger()
        logging.getLogger("paramiko").setLevel(logging.WARNING)
        logging.getLogger("paramiko.transport").setLevel(logging.WARNING)
        os.makedirs(cls._output_dir, exist_ok=True)
        cls._add_file_handler(logger)
        cls._add_console_handler(logger)
        
        cls._logger = logger
        return cls._logger
                
    @classmethod
    def log_msg(cls, msg: str, lvl: str = "INFO") -> None:
        """Log message with colored output."""
        log_color = cls.COLORS.get(lvl, cls.COLORS['RESET'])
        reset_color = cls.COLORS['RESET']
        
        msg = f"{log_color}{msg}{reset_color}"

        log_method = getattr(cls.logger, lvl.lower(), cls.logger.info)
        log_method(msg)
