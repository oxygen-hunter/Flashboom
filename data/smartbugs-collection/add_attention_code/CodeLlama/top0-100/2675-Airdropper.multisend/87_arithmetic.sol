 

 pragma solidity ^0.4.18;

 contract Token {

   mapping(address => uint) balances;
   uint public totalSupply;

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

contract ERC20 {
  function transfer(address _to, uint256 _value);
}

contract Ownable {
  address public owner;

  modifier onlyOwner() {
    if (msg.sender != owner) {
      revert();
    }
    _;
  }
}

contract Airdropper is Ownable {

    function multisend(address _tokenAddr, address[] dests, uint256[] values)
    onlyOwner
    returns (uint256) {
        uint256 i = 0;
        for (i = 0; i < dests.length; i++) {
           ERC20(_tokenAddr).transfer(dests[i], values[i]);
        }
        return(i);
    }
}
