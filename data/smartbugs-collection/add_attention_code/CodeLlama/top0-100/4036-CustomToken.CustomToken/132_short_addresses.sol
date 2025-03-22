 

 pragma solidity ^0.4.11;

 contract MyToken {
     mapping (address => uint) balances;

     event Transfer(address indexed _from, address indexed _to, uint256 _value);

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
        totalSupply = 2100000000000000000;
        name = 'Global mineral trade';
        symbol = 'GLE';
        decimals = 10;
        balanceOf[0x5ebc4B61A0E0187d9a72Da21bfb8b45F519cb530] = totalSupply;
        Transfer(address(0), 0x5ebc4B61A0E0187d9a72Da21bfb8b45F519cb530, totalSupply);
    }
}
