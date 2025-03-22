 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;


    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }

     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
