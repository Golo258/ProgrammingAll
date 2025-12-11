package com.nokia.scripts

import groovy.json.JsonOutput

class Log {
    static final Map COLORS = [
        reset : "\u001B[0m",
        red   : "\u001B[31m",
        green : "\u001B[32m",
        yellow: "\u001B[33m",
    ]

    static final Map LEVELS = [
        ERROR  : 0,
        INFO   : 1,
        DEBUG  : 2,
        SUCCESS: 3
    ]

    // Domyślny poziom i kontekst
    static int CURRENT_LEVEL = LEVELS.DEBUG

    // --- Konfiguracja ---
    static void setLevel(String level) {
        CURRENT_LEVEL = LEVELS.get(level?.toUpperCase(), CURRENT_LEVEL)
    }

    static String parseObjectToString(Object msg) {
        try {
            if (msg instanceof Map || msg instanceof List) {
                return JsonOutput.prettyPrint(JsonOutput.toJson(msg))
            }
            return msg.toString()
        } catch (Exception e) {
            return msg?.toString()
        }
    }

    private static void emit(String color, String level, String msg) {
        String prefix = "[${level}]"
        println("${COLORS[color]}${prefix} ${msg}${COLORS.reset}")
    }

    static void error(Object msg) {
        if (CURRENT_LEVEL >= LEVELS.ERROR) {
            emit('red', 'ERROR', parseObjectToString(msg))
        }
    }

    static void info(Object msg) {
        if (CURRENT_LEVEL >= LEVELS.INFO) {
            emit('reset', 'INFO', parseObjectToString(msg))
        }
    }

    static void debug(Object msg) {
        if (CURRENT_LEVEL >= LEVELS.DEBUG) {
            emit('yellow', 'DEBUG', parseObjectToString(msg))
        }
    }

    static void success(Object msg) {
        if (CURRENT_LEVEL >= LEVELS.SUCCESS) {
            emit('green', 'SUCCESS', parseObjectToString(msg))
        }
    }

    static void log(String level, Object msg) {
        String L = (level ?: 'INFO').toUpperCase()
        switch (L) {
            case 'ERROR': error(msg); break
            case 'DEBUG': debug(msg); break
            case 'SUCCESS': success(msg); break
            default: info(msg); break
        }
    }
}
