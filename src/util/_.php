<?hh // partial

namespace axolotl\util;

use axolotl\exceptions\BrokenInstallationException;

enum AXLSettingsFile: string{
  APP = "appconfig.json";
  SYS = "sysconfig.json";
}

class _{
  private static array<arraykey, mixed> $settings = array();

  public static function FILE(
    string $file, string $key, mixed $default = null
  ): mixed{
    if(!isset($_FILES[$file])){
      return $default ?? null;
    }
    return $_FILES[$file][$key] ?? $default ?? null;
  }

  public static function GET(arraykey $key): mixed{
    return $_GET[$key] ?? null;
  }

  public static function INI(string $key): mixed{
    return ini_get($key);
  }

  public static function POST(arraykey $key): mixed{
    return $_POST[$key] ?? null;
  }

  public static function SERVER(arraykey $key): mixed{
    return $_SERVER[$key] ?? null;
  }

  public static function SESSION(arraykey $key, mixed $value = null): mixed{
    if(session_status() !== 2){
      session_start();
    }
    if($value === null){
      return $_SESSION["axolotl"][$key] ?? null;
    }
    return $_SESSION["axolotl"][$key] = $value;
  }

  public static function SETTINGS(
    arraykey $key,
    mixed $stdval = null,
    AXLSettingsFile $file = AXLSettingsFile::SYS
  ): mixed{
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
    AXLSettingsFile $file = AXLSettingsFile::SYS
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
