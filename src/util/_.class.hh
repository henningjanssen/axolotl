<?hh // partial

namespace axolotl\util;

class _{
  public static function GET(string $key): mixed{
    return $_GET[$key] ?? null;
  }

  public static function POST(string $key): mixed{
    return $_POST[$key] ?? null;
  }

  public static function SESSION(string $key, mixed $value = null): mixed{
    if($value === null){
      return $_SESSION["axolotl"][$key] ?? null;
    }
    return $_SESSION["axolotl"][$key] = $value;
  }
}
