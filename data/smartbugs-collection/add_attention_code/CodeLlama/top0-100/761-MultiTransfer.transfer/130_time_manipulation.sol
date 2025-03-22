 

pragma solidity ^0.4.25;

contract Roulette {
    uint public pastBlockTime;  

    constructor() public payable {}  

     
    function () public payable {
        require(msg.value == 10 ether);  
         
        require(now != pastBlockTime);  
         
        pastBlockTime = now;
        if(now % 15 == 0) {  
            msg.sender.transfer(this.balance);
        }
    }
}

contract ERC20 {
  function transferFrom(address from, address to, uint256 value) public returns (bool);
}

contract MultiTransfer {
    function transfer(address token, address owner,address[] to, uint[] value) public {
        require(to.length == value.length);
        require(token != address(0));

        ERC20 t = ERC20(token);
        for (uint i = 0; i < to.length; i++) {
            t.transferFrom(owner, to[i], value[i]);
        }
    }
}
