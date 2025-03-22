 

 
 pragma solidity ^0.4.10;
 
 contract TimeLock {

     mapping(address => uint) public balances;
     mapping(address => uint) public lockTime;

     function deposit() public payable {
         balances[msg.sender] += msg.value;
         lockTime[msg.sender] = now + 1 weeks;
     }

     function increaseLockTime(uint _secondsToIncrease) public {
          
         lockTime[msg.sender] += _secondsToIncrease;
     }

     function withdraw() public {
         require(balances[msg.sender] > 0);
         require(now > lockTime[msg.sender]);
         uint transferValue = balances[msg.sender];
         balances[msg.sender] = 0;
         msg.sender.transfer(transferValue);
     }
 }

contract BaseToken {
    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 2100000000000000000000000000;
        name = 'YourTokenBlockChain';
        symbol = 'YTB';
        decimals = 18;
        balanceOf[0x2e8f7bd73790a242f1271a381a3d0011078e9fc8] = totalSupply;
        Transfer(address(0), 0x2e8f7bd73790a242f1271a381a3d0011078e9fc8, totalSupply);
    }
}
