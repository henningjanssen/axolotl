<?php

namespace axolotl\util;

class PathUtil{
	const MODULE_PATH = __DIR__.'/../../modules/';

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
