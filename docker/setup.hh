<?hh

$apacheConfig = '/system-data/apache-vhost.conf';
$axlSubDomain = getenv('APACHE_AXL_SUBDOMAIN');
if($axlSubDomain[strlen($axlSubDomain)-1] !== '/'){
  $axlSubDomain = "$axlSubDomain/";
}
if(file_exists($apacheConfig)){
  $fcontents = file_get_contents($apacheConfig);
  $webmaster = getenv('APACHE_WEBMASTER');
  $axlDomain = $axlSubDomain;
  $fcontents = str_replace(
    array("webmaster@localhost", "/AXL_DOMAIN/"),
    array($webmaster, $axlDomain),
    $fcontents
  );
  file_put_contents($apacheConfig, $fcontents);
}

$axlConf = '/axl/config/sysconfig.json';
if(file_exists($axlConf)){
  $fcontents = file_get_contents($axlConf);
  $jsonf = json_decode($fcontents, true);
  $jsonf['system']['base_uri'] = stripcslashes(
    substr($axlSubDomain, 0, -1)
  );
  $fcontents = json_encode($jsonf, JSON_PRETTY_PRINT);
  file_put_contents($axlConf, $fcontents);
}
