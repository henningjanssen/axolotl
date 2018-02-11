<?php

namespace axolotl\util;

use axolotl\exceptions\BrokenInstallationException;

class _{
  const SETTINGS_APP = "appconfig.json";
  const SETTINGS_SYS = "sysconfig.json";

  private static $settings = array();

  public static function FILE(
    string $file, string $key, $default = null
  ){
    if(!isset($_FILES[$file])){
      return $default ?? null;
    }
    return $_FILES[$file][$key] ?? $default ?? null;
  }

  public static function GET(string $key): ?string{
    return $_GET[$key] ?? null;
  }

  public static function INI(string $key){
    return ini_get($key);
  }

  public static function POST(string $key): ?string{
    return $_POST[$key] ?? null;
  }

  public static function SERVER(string $key): ?string{
    return $_SERVER[$key] ?? null;
  }

  public static function SESSION(string $key, $value = null){
    if(session_status() !== 2){
      session_start();
    }
    if($value === null){
      return $_SESSION["axolotl"][$key] ?? null;
    }
    return $_SESSION["axolotl"][$key] = $value;
  }

  public static function SETTINGS(
    string $key,
    $stdval = null,
    string $file = _::SETTINGS_SYS
  ){
    if(!is_array(self::$settings)
      || !array_key_exists($file, self::$settings)
      || count(self::$settings[$file]) === 0
    ){
      self::reloadSettings($file);
    }
    $keys = array($key);
    if(is_string($key) && strpos($key, ".") !== false){
      $keys = explode(".", $key);
    }
    $val = self::$settings[$file];
    foreach($keys as $k){
      if(!is_array($val)){
        $val = $stdval;
        break;
      }
      if(!array_key_exists($k, $val)){
        $val = $stdval;
        break;
      }
      $val = $val[$k];
    }
    return $val;
  }

  public static function reloadSettings(
    string $file = _::SETTINGS_SYS
  ): void{
    $configPath = realpath(__DIR__.'/../../config/'.$file);
    if(!file_exists($configPath)){
      throw new BrokenInstallationException("config-file {$file} is missing");
    }
    self::$settings[$file] = json_decode(
      file_get_contents($configPath), true
    );
    if(!is_array(self::$settings)
      || !array_key_exists($file, self::$settings)
      || count(self::$settings) === 0
    ){
      throw new BrokenInstallationException("config-file {$file} is malformed or empty");
    }
  }
}
