<?hh // partial

namespace axolotl\util;

use axolotl\exceptions\BrokenInstallationException;

class _{
  private static array<arraykey, mixed> $settings = array();

  public static function FILE(
    string $file, string $key, mixed $default = null
  ): mixed{
    if(!isset($_FILE[$file])){
      return $default ?? null;
    }
    return $_FILE[$file][$key] ?? null;
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

  public static function SETTINGS(arraykey $key, mixed $stdval = null): mixed{
    if(count(self::$settings) === 0){
      self::reloadSettings();
    }
    return self::$settings[$key] ?? $stdval;
  }

  public static function reloadSettings(): void{
    $configPath = realpath(__DIR__.'/../../config/config.json');
    if(!file_exists($configPath)){
      throw new BrokenInstallationException("config-file is missing");
    }
    self::$settings = json_decode(
      file_get_contents($configPath), true
    );
    if(!is_array(self::$settings) || count(self::$settings) === 0){
      throw new BrokenInstallationException("config-file is malformed or empty");
    }
  }
}
