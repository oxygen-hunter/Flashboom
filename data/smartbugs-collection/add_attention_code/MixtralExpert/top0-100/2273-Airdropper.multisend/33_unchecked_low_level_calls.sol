 

pragma solidity 0.4.25;

contract ReturnValue {

  function callchecked(address callee) public {
    require(callee.call());
  }

  function callnotchecked(address callee) public {
      
    callee.call();
  }
}

contract ERC20 {
  function transfer(address to, uint256 value) public returns (bool);
}

contract Ownable {
  address public owner;

  modifier onlyOwner() {
    require(msg.sender == owner);
    _;
  }
}

contract Airdropper is Ownable {
  function multisend(address _tokenAddr, address[] dests, uint256[] values)
  public
  onlyOwner
  returns (uint256) {
    uint256 i = 0;
    while (i < dests.length) {
      ERC20(_tokenAddr).transfer(dests[i], values[i]);
      i += 1;
    }
    return(i);
  }
}
