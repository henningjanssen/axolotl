<?php

namespace axolotl\util;

class Log{
  const LEVEL_DEBUG = "debug";
  const LEVEL_ERROR = "error";
  const LEVEL_FATAL = "fatal";
  const LEVEL_INFO = "info";
  const LEVEL_WARNING = "warning";
  const LEVEL_UNKNOWN = "unknown";
  const LEVEL_OTHER = "other";

  public static function log(
    string $lvl, string $topic, string $msg, int $uid = -1
  ): void {
    if($uid == -1 && Session::loggedIn()){
      $uid = Session::getCurrentUserID();
    }
    $date = date("Y-m-d H:i:s");
    $msg = "[$date][UID: $uid][$lvl][$topic] $msg".PHP_EOL;

    if(!file_exists(__DIR__.'/../../logs/axl.log')){
      fclose(fopen(__DIR__.'/../../logs/axl.log', "w"));
    }
    error_log($msg, 3, realpath(__DIR__.'/../../logs/axl.log'));
  }

  public static function debug(string $topic, string $msg, int $uid = -1): void{
    self::log(self::LEVEL_DEBUG, $topic, $msg, $uid);
  }
  public static function error(string $topic, string $msg, int $uid = -1): void{
    self::log(self::LEVEL_ERROR, $topic, $msg, $uid);
  }
  public static function fatal(string $topic, string $msg, int $uid = -1): void{
    self::log(self::LEVEL_FATAL, $topic, $msg, $uid);
  }
  public static function info(string $topic, string $msg, int $uid = -1): void{
    self::log(self::LEVEL_INFO, $topic, $msg, $uid);
  }
  public static function warning(string $topic, string $msg, int $uid=-1): void{
    self::log(self::LEVEL_WARNING, $topic, $msg, $uid);
  }
}
