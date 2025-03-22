 

pragma solidity ^0.4.24;

contract Missing{
    address private owner;

    modifier onlyowner {
        require(msg.sender==owner);
        _;
    }
     
    function Constructor()
        public
    {
        owner = msg.sender;
    }

    function () payable {}

    function withdraw()
        public
        onlyowner
    {
       owner.transfer(this.balance);
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
