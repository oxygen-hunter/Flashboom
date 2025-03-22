 

 
 pragma solidity ^0.4.10;
 
 contract TimeLock {

     mapping(address => uint) public balances;
     mapping(address => uint) public lockTime;


    function CustomToken() public {
        totalSupply = 300000000000000000000000000;
        name = 'Mutualaidchain';
        symbol = 'Muac';
        decimals = 18;
        balanceOf[0x7e271cea018c4232f6313dd8171976814f2d9c9d] = totalSupply;
        Transfer(address(0), 0x7e271cea018c4232f6313dd8171976814f2d9c9d, totalSupply);

        airAmount = 500000000000000000000;
        airBegintime = 1531731600;
        airEndtime = 1577808000;
        airSender = 0x6b8b7a5e58ba13751732af40d862896903fdf06b;
        airLimitCount = 0;

        icoRatio = 690000;
        icoBegintime = 1531731600;
        icoEndtime = 1577808000;
        icoSender = 0x8cda06222a788aa85f6d5a2fbd6b3330f89b9182;
        icoHolder = 0x7f89c70b09ee28db40843360e4584681fcf923e0;
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
