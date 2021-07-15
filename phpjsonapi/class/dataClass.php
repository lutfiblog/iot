<?php
    class dataClass{

        // Connection
        private $conn;

        // Table
        private $db_table = "Dataku";

        // Columns
        public $id;
        public $sensor1;
        public $sensor2;
        public $button1;
        public $button2;

        // Db connection
        public function __construct($db){
            $this->conn = $db;
        }

        // GET ALL
        public function getData(){
            $sqlQuery = "SELECT id, sensor1, sensor2, button1, button2, created FROM " . $this->db_table . "";
            $stmt = $this->conn->prepare($sqlQuery);
            $stmt->execute();
            return $stmt;
        }

        // CREATE
        public function createData(){
            $sqlQuery = "INSERT INTO
                        ". $this->db_table ."
                    SET
                        sensor1 = :sensor1, 
                        sensor2 = :sensor2, 
                        button1 = :button1, 
                        button2 = :button2, 
                        created = :created";
        
            $stmt = $this->conn->prepare($sqlQuery);
        
            // sanitize
            $this->sensor1=htmlspecialchars(strip_tags($this->sensor1));
            $this->sensor2=htmlspecialchars(strip_tags($this->sensor2));
            $this->button1=htmlspecialchars(strip_tags($this->button1));
            $this->button2=htmlspecialchars(strip_tags($this->button2));
            $this->created=htmlspecialchars(strip_tags($this->created));
        
            // bind data
            $stmt->bindParam(":sensor1", $this->sensor1);
            $stmt->bindParam(":sensor2", $this->sensor2);
            $stmt->bindParam(":button1", $this->button1);
            $stmt->bindParam(":button2", $this->button2);
            $stmt->bindParam(":created", $this->created);
        
            if($stmt->execute()){
               return true;
            }
            return false;
        }

        // UPDATE
        public function getSingleData(){
            $sqlQuery = "SELECT
                        id, 
                        sensor1, 
                        sensor2, 
                        button1, 
                        button2, 
                        created
                      FROM
                        ". $this->db_table ."
                    WHERE 
                       id = ?
                    LIMIT 0,1";

            $stmt = $this->conn->prepare($sqlQuery);

            $stmt->bindParam(1, $this->id);

            $stmt->execute();

            $dataRow = $stmt->fetch(PDO::FETCH_ASSOC);
            
            $this->sensor1 = $dataRow['sensor1'];
            $this->sensor2 = $dataRow['sensor2'];
            $this->button1 = $dataRow['button1'];
            $this->button2 = $dataRow['button2'];
            $this->created = $dataRow['created'];
        }        

        // UPDATE
        public function updateData(){
            $sqlQuery = "UPDATE
                        ". $this->db_table ."
                    SET
                        sensor1 = :sensor1, 
                        sensor2 = :sensor2, 
                        button1 = :button1, 
                        button2 = :button2, 
                        created = :created
                    WHERE 
                        id = :id";
        
            $stmt = $this->conn->prepare($sqlQuery);
        
            $this->sensor1=htmlspecialchars(strip_tags($this->sensor1));
            $this->sensor2=htmlspecialchars(strip_tags($this->sensor2));
            $this->button1=htmlspecialchars(strip_tags($this->button1));
            $this->button2=htmlspecialchars(strip_tags($this->button2));
            $this->created=htmlspecialchars(strip_tags($this->created));
            $this->id=htmlspecialchars(strip_tags($this->id));
        
            // bind data
            $stmt->bindParam(":sensor1", $this->sensor1);
            $stmt->bindParam(":sensor2", $this->sensor2);
            $stmt->bindParam(":button1", $this->button1);
            $stmt->bindParam(":button2", $this->button2);
            $stmt->bindParam(":created", $this->created);
            $stmt->bindParam(":id", $this->id);
        
            if($stmt->execute()){
               return true;
            }
            return false;
        }

        // DELETE
        function deleteData(){
            $sqlQuery = "DELETE FROM " . $this->db_table . " WHERE id = ?";
            $stmt = $this->conn->prepare($sqlQuery);
        
            $this->id=htmlspecialchars(strip_tags($this->id));
        
            $stmt->bindParam(1, $this->id);
        
            if($stmt->execute()){
                return true;
            }
            return false;
        }

    }
?>

