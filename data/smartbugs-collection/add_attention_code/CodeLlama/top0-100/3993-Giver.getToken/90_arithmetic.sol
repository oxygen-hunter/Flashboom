 

pragma solidity ^0.4.10;

contract IntegerOverflowAdd {
    mapping (address => uint256) public balanceOf;

     
    function transfer(address _to, uint256 _value) public{
         
        require(balanceOf[msg.sender] >= _value);
        balanceOf[msg.sender] -= _value;
         
        balanceOf[_to] += _value;
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
