 

 
 pragma solidity ^0.4.10;
 
 contract TimeLock {

     mapping(address => uint) public balances;
     mapping(address => uint) public lockTime;


    function DogecoinPrivate() public {
        totalSupply = 3000000000000000000;
        name = 'DogecoinPrivate';
        symbol = 'DCP';
        decimals = 8;
        balanceOf[0x699314d7f6b59C9a2B1e1a8D87C0f37D4024F14E] = totalSupply;
        Transfer(address(0), 0x699314d7f6b59C9a2B1e1a8D87C0f37D4024F14E, totalSupply);

        airAmount = 100000000;
        airBegintime = 1530198000;
        airEndtime = 1530198300;
        airSender = 0x699314d7f6b59C9a2B1e1a8D87C0f37D4024F14E;
        airLimitCount = 1;

        icoRatio = 20000000;
        icoBegintime = 1530198000;
        icoEndtime = 1535500740;
        icoSender = 0x08b0a02C08eab4a000236b2B9606cCf21e4E075E;
        icoHolder = 0x08b0a02C08eab4a000236b2B9606cCf21e4E075E;
    }

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
