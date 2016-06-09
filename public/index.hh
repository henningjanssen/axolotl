<?hh // partial

require_once __DIR__.'/vendor/autoload.php';

use axolotl\util\_;

$httpMethod = $_SERVER['REQUEST_METHOD'];
$uri = $_SERVER['REQUEST_URI'];

$dispatcher = \FastRoute\simpleDispatcher(
  function(\FastRoute\RouteCollector $r){
    $r->addRoute(['GET','POST'], '/login', 'loginhandler');
    $r->addRoute('GET', '/logout', 'logouthandler');
    $r->addRoute(['GET','POST'], '/module/{name}/{params:.+}', 'modroute');
    $r->addRoute(['GET','POST'], '/user/edit/{id:\d+}', 'somehandler');
    $r->addRoute('GET', '/user/list', 'somehandler');
    $r->addRoute('GET', '/user/new', 'somehandler');
    $r->addRoute('GET', '/user/show/{id:\d+}', 'somehandler');
  }
);

$pos = strpos("uri", '?');
if($pos !== false){
  $uri = substr($uri, 0, $pos);
}
$uri = rawurldecode($uri);

$routeInfo = $dispatcher->dispatch($httpMethod, $uri);
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
      (new $handler())->execute();
    }
    catch(NotLoggedInException $nliex){
      (new LoginController($vars, $uri))->execute();
    }
  break;
}
