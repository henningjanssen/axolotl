<?hh // strict

namespace axolotl\util;

class PathUtil{
	const string MODULE_PATH = self::ROOT . 'modules/';
	const string ROOT = __DIR__ . '/../../';

	public static function deleteDirectory(string $dir): void{
		$delIt = new \RecursiveDirectoryIterator($dir,
			\RecursiveDirectoryIterator::SKIP_DOTS
		);
		$delFiles = new \RecursiveIteratorIterator($delIt,
			\RecursiveIteratorIterator::CHILD_FIRST
		);
		foreach($delFiles as $delf){
			if($delf->isDir()){
				rmdir($delf->getRealPath());
			}
			else{
				unlink($delf->getRealPath());
			}
		}
		rmdir($dir);
	}
}
