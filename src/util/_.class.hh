<?hh // partial

namespace axolotl\util;

use axolotl\exceptions\BrokenInstallationException;

class _{
  private static array<string, mixed> $settings = array();
  public static function GET(string $key): mixed{
    return $_GET[$key] ?? null;
  }

  public static function POST(string $key): mixed{
    return $_POST[$key] ?? null;
  }

  public static function SERVER(string $key): mixed{
    return $_SERVER[$key] ?? null;
  }

  public static function SESSION(string $key, mixed $value = null): mixed{
    if($value === null){
      return $_SESSION["axolotl"][$key] ?? null;
    }
    return $_SESSION["axolotl"][$key] = $value;
  }

  public static function SETTINGS(string $key){
    if(count(self::$settings) === 0){
      $configPath = realpath(__DIR__.'/../../config/config.json');
      if(!file_exists($configPath)){
        throw new BrokenInstallationException("config-file is missing");
      }
      self::$settings = json_decode(
        file_get_contents($configPath)
      );
      if(!is_array(self::$settings) || count(self::$settings) === 0){
        throw new BrokenInstallationException("config-file is malformed");
      }
    }
    return self::$settings[$key] ?? null;
  }
}
