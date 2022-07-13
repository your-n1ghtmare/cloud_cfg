<?php

$dsn = "mysql:host=$host;dbname=$db;charset=$charset";
$opt = 
[
PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
PDO::ATTR_EMULATE_PREPARES   => false,
];

$pdo = new PDO( $dsn, $dbuser, $pass, $opt );
$conn = mysqli_connect($host, $dbuser, $pass, $db);


if ( isset( $_GET[ "username" ] ) )
{
	require( 'src/XF.php' );
	XF::start( $fileDir );
	$app = \XF::setupApp( 'XF\App' );

	$ip = $app->request->getIp( );

    $finder = \XF::finder( 'XF:User' );
	$user = $finder->where( 'username', $_GET[ "username" ] )->fetchOne( );

    $file_directory = 'data/cfg/' . $user[ "user_id" ] . '.txt';

    if ( isset( $_GET[ "upload" ] ) ) {

        $input = json_decode(file_get_contents("php://input"), true);

        $f = fopen($file_directory, 'w');

        fwrite($f, json_encode($input));

        fclose($f);
    }

    else if ( isset( $_GET[ "get" ] ) ) {
          
        if(file_exists($file_directory)) {
            $homepage = file_get_contents($file_directory);
            echo $homepage;
        }
    }
}
