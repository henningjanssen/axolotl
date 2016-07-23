<?hh // partial

namespace axolotl\control;

use axolotl\exceptions\NotLoggedInException;
use axolotl\util\_;

class ApplicationControl{
  public function __construct(private string $uri, private string $httpMethod){}

  public function execute(): void{
    $dispatcher = \FastRoute\simpleDispatcher(
      function(\FastRoute\RouteCollector $r){
        $ns = "\\axolotl\\control";
        $r->addRoute('GET', '[/[home]]',"$ns\\HomePageControl");
        $r->addRoute(['GET','POST'], '/login', "$ns\\LoginControl");
        $r->addRoute('GET', '/logout', "$ns\\LogoutControl");
        $r->addRoute(['GET','POST'], '/module/{name}/{params:.+}', 'modroute');
        $r->addRoute(['GET','POST'], '/user/edit/{id:\d+}', 'somehandler');
        $r->addRoute('GET', '/user/list', 'somehandler');
        $r->addRoute('GET', '/user/new', 'somehandler');
        $r->addRoute('GET', '/user/show/{id:\d+}', 'somehandler');
        $r->addRoute('GET', '/about', "$ns\\AboutControl");
      }
    );

    $pos = strpos($this->uri, '?');
    if($pos !== false){
      $this->uri = substr($this->uri, 0, $pos);
    }
    $pos = strpos($this->uri, _::SETTINGS("axolotl_base_uri"));
    if($pos === 0){
      $this->uri = substr($this->uri, strlen(_::SETTINGS("axolotl_base_uri")));
    }
    if($this->uri[0] !== '/'){
      $this->uri = "/$this->uri";
    }
    $this->uri = rawurldecode($this->uri);

    $routeInfo = $dispatcher->dispatch($this->httpMethod, $this->uri);
    switch($routeInfo[0]){
      case \FastRoute\Dispatcher::NOT_FOUND:
        //404
      break;

      case \FastRoute\Dispatcher::METHOD_NOT_ALLOWED:
        //405 Method not allowed
      break;

      case \FastRoute\Dispatcher::FOUND:
        $handler = $routeInfo[1];
        $vars = $routeInfo[2];
        try{
          (new $handler($vars))->execute();
        }
        catch(NotLoggedInException $nliex){
          (new LoginControl($vars, $this->uri))->execute();
        }
      break;
    }
  }
}
