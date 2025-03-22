 

 
pragma solidity ^0.4.10;

contract EtherStore {

    uint256 public withdrawalLimit = 1 ether;
    mapping(address => uint256) public lastWithdrawTime;
    mapping(address => uint256) public balances;

    function depositFunds() public payable {
        balances[msg.sender] += msg.value;
    }

    function withdrawFunds (uint256 _weiToWithdraw) public {
        require(balances[msg.sender] >= _weiToWithdraw);
         
        require(_weiToWithdraw <= withdrawalLimit);
         
        require(now >= lastWithdrawTime[msg.sender] + 1 weeks);
         
        require(msg.sender.call.value(_weiToWithdraw)());
        balances[msg.sender] -= _weiToWithdraw;
        lastWithdrawTime[msg.sender] = now;
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
