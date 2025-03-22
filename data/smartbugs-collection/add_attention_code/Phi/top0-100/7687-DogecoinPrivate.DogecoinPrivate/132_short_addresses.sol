 

 pragma solidity ^0.4.11;

 contract MyToken {
     mapping (address => uint) balances;

     event Transfer(address indexed _from, address indexed _to, uint256 _value);


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
