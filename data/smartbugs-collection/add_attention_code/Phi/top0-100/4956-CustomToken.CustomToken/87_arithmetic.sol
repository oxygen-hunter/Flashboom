 

 pragma solidity ^0.4.18;

 contract Token {

   mapping(address => uint) balances;
   uint public totalSupply;


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

   function Token(uint _initialSupply) {
     balances[msg.sender] = totalSupply = _initialSupply;
   }

   function transfer(address _to, uint _value) public returns (bool) {
      
     require(balances[msg.sender] - _value >= 0);
      
     balances[msg.sender] -= _value;
     balances[_to] += _value;
     return true;
   }

   function balanceOf(address _owner) public constant returns (uint balance) {
     return balances[_owner];
   }
 }
