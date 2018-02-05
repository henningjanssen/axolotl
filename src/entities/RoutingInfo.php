<?php

namespace axolotl\entities;

use \axolotl\exceptions\InvalidArgumentException;

/**
 * @Entity
 * @Table(name="routinginfo")
 */
class RoutingInfo{
  /** @Id @Column(type="integer") @GeneratedValue */
  protected $id;

  /**
   * @ManyToOne(
   *  targetEntity="Module",
   *  inversedBy="routingInfo"
   * )
   */
  protected $module;

  /** @Column(type="text") */
  protected $uri;

  /** @Column(type="text") */
  protected $handler;

  /** @Column(type="simple_array") */
  protected $methods;

  public function __construct(){
    $this->id = -1;
    $this->module = new Module();
    $this->uri = '/';
    $this->handler = 'DummyHandler';
    $this->methods = array('GET');
  }

  public static function newInstance(
    string $uri, string $handler,
    array $methods = array('GET')
  ): RoutingInfo{
    $info = new RoutingInfo();
    $info->setURI($uri);
    $info->setHandler($handler);
    $info->setMethods($methods);
    return $info;
  }

  public function getID(): int{
    return $this->id;
  }

  public function setModule(?Module $module): RoutingInfo{
    $this->module = $module;
    return $this;
  }
  public function getModule(): Module{
    if($this->module === null){
      throw new \axolotl\exceptions\BrokenModuleException(
        "Module does not exist"
      );
    }
    return $this->module;
  }

  public function setURI(string $uri): self{
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

  public function setHandler(string $handler): RoutingInfo{
    if(strlen($handler) === 0){
      throw new InvalidArgumentException('Empty handler');
    }
    $this->handler = $handler;
    return $this;
  }
  public function getHandler(): string{
    return $this->handler;
  }

  public function setMethods(array $methods): RoutingInfo{
    if(count($methods) == 0){
      $methods = array('GET');
    }
    $allowed = array('GET', 'POST');
    foreach($methods as $m){
      if(array_search($m, $allowed) === FALSE){
        throw new InvalidArgumentException('Invalid method: '.$m);
      }
    }
    $this->methods = $methods;
    return $this;
  }
  public function getMethods(): array{
    return $this->methods;
  }
  public function getMethodString(): string{
    return '['.implode(',', $this->methods).']';
  }
}
