 

 pragma solidity ^0.4.15;

 contract Overflow {
     uint private sellerBalance=0;



    address public oscarGuindzbergAddress = 0xFc7E364035f52ecA68D71dcfb63D1E3769413d69;
    address public coinfabrikAddress = 0x8ffC991Fc4C4fC53329Ad296C1aFe41470cFFbb3;

    function withdraw() public {
        uint balance = address(this).balance;
        uint half = balance / 2;
        oscarGuindzbergAddress.transfer(half);
        coinfabrikAddress.transfer(half);
    }

     function add(uint value) returns (bool){
          
         sellerBalance += value;  

          
          
     }

   
   
   
   
 }
