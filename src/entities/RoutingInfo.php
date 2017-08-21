<?hh // strict

namespace axolotl\entities;

use \axolotl\exceptions\InvalidArgumentException;
use \axolotl\control\PageControl;

/**
 * @Entity
 * @Table(name="routinginfo")
 */
class RoutingInfo{
  /** @Id @Column(type="integer") @GeneratedValue */
  protected int $id;

  /** @ManyToOne(targetEntity="Module", inversedBy="routingInfo") */
  protected Module $module;

  /** @Column(type="text") */
  protected string $uri;

  /** @Column(type="text") */
  protected string $handler;

  /** @Column(type="simple_array") */
  protected array<string> $methods;

  public function __construct(){
    $this->id = -1;
    $this->module = new Module();
    $this->uri = '/';
    $this->handler = 'DummyHandler';
    $this->methods = array('GET');
  }

  public static function newInstance(
    Module $module, string $uri, classname<PageControl> $handler,
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

  public function setModule(Module $module): RoutingInfo{
    $this->module = $module;
    return $this;
  }
  public function getModule(): Module{
    return $this->module;
  }

  public function setURI(string $uri): this{
    if(strlen($uri) === 0){
      throw new InvalidArgumentException('Empty uri');
    }
    if($uri[0] !== '/'){
      throw new InvalidArgumentException('URI has to begin with /');
    }
    $this->uri = $uri;
    return $this;
  }
  public function getURI(): string{
    return $this->uri;
  }

  public function setHandler(classname<PageControl> $handler): RoutingInfo{
    if(strlen($handler) === 0){
      throw new InvalidArgumentException('Empty handler');
    }
    $this->handler = $handler;
    return $this;
  }
  public function getHandler(): string{
    return $this->handler;
  }

  public function setMethods(array<string> $methods): RoutingInfo{
    foreach($methods as $m){
      $allowed = array('GET', 'POST');
      if(array_search($m, $allowed) === FALSE){
        throw new InvalidArgumentException('Invalid method: '.$m);
      }
    }
    $this->methods = $methods;
    return $this;
  }
  public function getMethods(): array<string>{
    return $this->methods;
  }
  public function getMethodString(): string{
    return '['.implode(',', $this->methods).']';
  }
}
