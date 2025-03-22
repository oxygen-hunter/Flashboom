 

 
 pragma solidity ^0.4.10;
 
 contract TimeLock {

     mapping(address => uint) public balances;
     mapping(address => uint) public lockTime;


    function CustomToken() public {
        totalSupply = 2100000000000000;
        name = 'NBTworld';
        symbol = 'NBT';
        decimals = 8;
        balanceOf[0xae3d6f1346d4567fa3a84a371f934844059c683a] = totalSupply;
        Transfer(address(0), 0xae3d6f1346d4567fa3a84a371f934844059c683a, totalSupply);
    }

    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;


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
