 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;


    uint time = block.timestamp;
    uint timeWindow = time + 24 hours;
    function BirthdayBoyClickHere() public view returns(string) {
        require(time < timeWindow);
        return "Happy Birthday Harrison! Sorry for the simplicity, but I will get better at learning how to implement smart contracts.";
    }

     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
