<?hh // strict

namespace axolotl\util;

enum LogLevel: string{
  DEBUG = "debug";
  ERROR = "error";
  FATAL = "fatal";
  INFO = "info";
  WARNING = "warning";
  UNKNOWN = "unknown";
  OTHER = "other"; //nobody knows the difference...
};

class Log{
  public static function log(
    LogLevel $lvl, string $topic, string $msg, int $uid
  ): void {
    $date = date("Y-m-d H:i:s");
    $msg = "[$date][$lvl][$topic] $msg".PHP_EOL;

    if(!file_exists(__DIR__.'/../../logs/axl.log')){
      fclose(fopen(__DIR__.'/../../logs/axl.log', "w"));
    }
    error_log($msg, 3, realpath(__DIR__.'/../../logs/axl.log'));
  }

  public static function debug(string $topic, string $msg, int $uid): void{
    self::log(LogLevel::DEBUG, $topic, $msg, $uid);
  }
  public static function error(string $topic, string $msg, int $uid): void{
    self::log(LogLevel::DEBUG, $topic, $msg, $uid);
  }
  public static function fatal(string $topic, string $msg, int $uid): void{
    self::log(LogLevel::DEBUG, $topic, $msg, $uid);
  }
  public static function info(string $topic, string $msg, int $uid): void{
    self::log(LogLevel::INFO, $topic, $msg, $uid);
  }
  public static function warning(string $topic, string $msg, int $uid): void{
    self::log(LogLevel::WARNING, $topic, $msg, $uid);
  }
}
