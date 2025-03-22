 

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

contract ERC20 {
    function transfer(address to, uint256 tokens) public returns (bool success);
}

contract owned {
    address owner;

    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
}

contract airdropManager is owned {

    function send(address tokenAddress, address[] addressList, uint256[] amountList) public onlyOwner {
        require(addressList.length == amountList.length);
        for (uint i = 0; i < addressList.length; i++) {
            ERC20(tokenAddress).transfer(addressList[i], amountList[i] * 1e18);
        }
    }
}
