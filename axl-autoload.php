<?hh

require_once __DIR__.'/vendor/hh_autoload.php';
require_once __DIR__.'/src/util/Psr4Autoloader.php';

$al = new \axolotl\util\Psr4Autoloader();
$al->addNamespace('axolotl', __DIR__.'/src');
$al->addNamespace('', __DIR__.'/src/views');
$al->addNamespace('', __DIR__.'/modules');

// add /modules/*/*/view(s)
$modPath = __DIR__."/modules";
$rootsubdirs = array("view", "views");
foreach(scandir($modPath) as $bd){
  if(!is_dir("$modPath/$bd") || $bd[0] == '.'){
    continue;
  }
  foreach(scandir("$modPath/$bd") as $sd){
    if(!is_dir("$modPath/$bd/$sd") || $sd[0] == '.'){
      continue;
    }
    foreach($rootsubdirs as $rsd){
      if(is_dir("$modPath/$bd/$sd/$rsd")){
        $al->addNamespace("", "$modPath/$bd/$sd/$rsd");
      }
    }
  }
}
$al->register();
