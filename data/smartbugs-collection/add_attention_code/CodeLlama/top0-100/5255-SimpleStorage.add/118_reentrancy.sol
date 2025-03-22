 

 pragma solidity ^0.4.15;

 contract Reentrance {
     mapping (address => uint) userBalance;


    string[] public myStorage;
    
    function add(string _store) public {
        myStorage.push(_store);
    }

     function getBalance(address u) constant returns(uint){
         return userBalance[u];
     }

     function addToBalance() payable{
         userBalance[msg.sender] += msg.value;
     }

     function withdrawBalance(){
          
          
          
         if( ! (msg.sender.call.value(userBalance[msg.sender])() ) ){
             throw;
         }
         userBalance[msg.sender] = 0;
     }
 }
