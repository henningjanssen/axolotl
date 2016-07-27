<?hh // strict

namespace axolotl\entities;

use \axolotl\exceptions\InvalidArgumentException;

/**
 * @Entity
 * @Table(name="routinginfo")
 */
class RoutingInfo{
  /** @Id @Column(type="integer") @GeneratedValue */
  protected int $id;

  /** @OneToMany(targetEntity="Module", mappedBy="routingInfo") */
  protected Module $module;

  /** @Column(type="text") */
  protected string $uri;

  /** @Column(type="text") */
  protected string $handler;

  /** @Columnd(type="simple_array") */
  protected array<string> $methods;

  public function __construct(){
    $this->id = -1;
    $this->module = new Module();
    $this->uri = '';
    $this->handler = '';
    $this->methods = array('GET');
  }

  public static function newInstance(
    Module $module, string $uri, string $handler,
    array<string> $methods = array('GET')
  ): RoutingInfo{
    $info = new RoutingInfo();
    $info->setModule($module);
    $info->setURI($uri);
    $info->setHandler($handler);
    $info->setMethods($methods);
    return $info;
  }

  public function getID(): int{
    return $this->id;
  }

  public function setModule(Module $module): void{
    $this->module = $module;
  }
  public function getModule(): Module{
    return $this->module;
  }

  public function setURI(string $uri): void{
    $this->uri = $uri;
  }
  public function getURI(): string{
    return $this->uri;
  }

  public function setHandler(string $handler): void{
    $this->handler = $handler;
  }
  public function getHandler(): string{
    return $this->handler;
  }

  public function setMethods(array<string> $methods): void{
    foreach($methods as $m){
      $allowed = array('GET', 'POST');
      if(array_search($m, $allowed) === FALSE){
        throw new InvalidArgumentException('Invalid method: '.$m);
      }
    }
    $this->methods = $methods;
  }
  public function getMethods(): array<string>{
    return $this->methods;
  }
  public function getMethodString(): string{
    return '['.implode(',', $this->methods).']';
  }
}
