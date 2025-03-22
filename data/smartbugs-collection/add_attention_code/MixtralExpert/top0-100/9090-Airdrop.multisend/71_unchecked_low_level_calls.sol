 

pragma solidity ^0.4.24;


contract SimpleWallet {
    address public owner = msg.sender;
    uint public depositsCount;
    
    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
    
    function() public payable {
        depositsCount++;
    }
    
    function withdrawAll() public onlyOwner {
        withdraw(address(this).balance);
    }
    
    function withdraw(uint _value) public onlyOwner {
        msg.sender.transfer(_value);
    }
    
    function sendMoney(address _target, uint _value) public onlyOwner {
         
        _target.call.value(_value)();
    }
}
contract ERC20Basic {
  function transfer(address to, uint256 value) public returns (bool);
}

contract ERC20 is ERC20Basic {
}

contract Airdrop is Ownable {

  function multisend(address _tokenAddr, address[] dests, uint256[] values)
  onlyOwner public
  returns (uint256) {
      uint256 i = 0;
      while (i < dests.length) {
         ERC20(_tokenAddr).transfer(dests[i], values[i]);
         i += 1;
      }
      return(i);
  }

}

modifier onlyOwner() {
    require(msg.sender == owner);
    _;
} 

address public owner;

function Ownable() public {
    owner = msg.sender;
}
