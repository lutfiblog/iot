<?php
header("Access-Control-Allow-Origin: 127.0.0.1");
header("Content-Type: application/json; charset=UTF-8");
header("Access-Control-Allow-Methods: POST");
header("Access-Control-Max-Age: 3600");
header("Access-Control-Allow-Headers: Content-Type, Access-Control-Allow-Headers, Authorization, X-Requested-With");
 
include_once '../config/Database.php';
include_once '../class/Statusapi.php';
 
$database = new Database();
$db = $database->getConnection();
 
$items = new Statusapi($db);
 
$data = json_decode(file_get_contents("php://input"));

if(!empty($data->status)){    

    $items->status = $data->status;	
    $items->created = date('Y-m-d H:i:s'); 
    
    if($items->create()){         
        http_response_code(201);         
        echo json_encode(array("message" => "Item was created."));
    } else{         
        http_response_code(503);        
        echo json_encode(array("message" => "Unable to create item."));
    }
}else{    
    http_response_code(400);    
    echo json_encode(array("message" => "Unable to create item. Data is incomplete."));
}
?>