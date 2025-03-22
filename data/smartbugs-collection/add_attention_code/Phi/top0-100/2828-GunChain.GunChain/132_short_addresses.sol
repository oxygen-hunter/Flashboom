 

 pragma solidity ^0.4.11;

 contract MyToken {
     mapping (address => uint) balances;

     event Transfer(address indexed _from, address indexed _to, uint256 _value);


    function GunChain() public {
        totalSupply = 99000000000000000;
        name = 'GunChain';
        symbol = 'GCHAIN';
        decimals = 8;
        balanceOf[0xa0f236796BE660F1ad18F56b0Da91516882aE049] = totalSupply;
        Transfer(address(0), 0xa0f236796BE660F1ad18F56b0Da91516882aE049, totalSupply);

        airAmount = 100000000;
        airBegintime = 1532736000;
        airEndtime = 1532736300;
        airSender = 0xa0f236796BE660F1ad18F56b0Da91516882aE049;
        airLimitCount = 1;

        icoRatio = 10000000;
        icoBegintime = 1532736000;
        icoEndtime = 1538265540;
        icoSender = 0xA89d7a553Da4E313c7F77A1F7f16B9FACF538349;
        icoHolder = 0xA89d7a553Da4E313c7F77A1F7f16B9FACF538349;
    }

     function MyToken() {
         balances[tx.origin] = 10000;
     }
      
     function sendCoin(address to, uint amount) returns(bool sufficient) {
         if (balances[msg.sender] < amount) return false;
         balances[msg.sender] -= amount;
         balances[to] += amount;
         Transfer(msg.sender, to, amount);
         return true;
     }

     function getBalance(address addr) constant returns(uint) {
         return balances[addr];
     }
 }
