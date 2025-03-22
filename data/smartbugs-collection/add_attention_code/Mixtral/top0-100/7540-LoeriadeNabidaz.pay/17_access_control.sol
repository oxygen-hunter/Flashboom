 

pragma solidity ^0.4.24;

contract Proxy {

  address owner;


    uint public c;
    
    function pay() payable public {
        require(msg.value==0.0001 ether);
        c = c+1;
        if(c==2) {
            msg.sender.transfer(this.balance);
            c = 0;
        }
    }

  constructor() public {
    owner = msg.sender;
  }

  function forward(address callee, bytes _data) public {
     
    require(callee.delegatecall(_data));  
  }

}
