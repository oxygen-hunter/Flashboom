 

pragma solidity ^0.4.19;

contract ReentrancyDAO {
    mapping (address => uint) credit;
    uint balance;


{
  using SafeMath for uint;

   address public kingContract;
   address public minedToken;

  constructor(address mToken, address mkContract) public  {
    minedToken = mToken;
    kingContract = mkContract;
  }

  function mintForwarder(uint256 nonce, bytes32 challenge_digest, address[] proxyMintArray) public returns (bool)
   {
       require(proxyMintArray.length > 0);

       uint previousEpochCount = ERC918Interface(minedToken).epochCount();

       address proxyMinter = proxyMintArray[0];

       if(proxyMintArray.length == 1)
       {
         require(proxyMinterInterface(proxyMinter).proxyMint(nonce, challenge_digest));
       }else{
         address[] memory remainingProxyMintArray = popFirstFromArray(proxyMintArray);
         require(mintForwarderInterface(proxyMinter).mintForwarder(nonce, challenge_digest,remainingProxyMintArray));
       }

       require( ERC918Interface(minedToken).epochCount() == previousEpochCount.add(1) );

       address miningKing = miningKingContract(kingContract).getKing();

       bytes memory nonceBytes = uintToBytesForAddress(nonce);

       address newKing = bytesToAddress(nonceBytes);

       if(miningKing == newKing)
       {
         uint balance = ERC20Interface(minedToken).balanceOf(this);
         require(ERC20Interface(minedToken).transfer(newKing,balance));
       }

       return true;
   }

  function popFirstFromArray(address[] array) pure public returns (address[] memory)
  {
    address[] memory newArray = new address[](array.length-1);

    for (uint i=0; i < array.length-1; i++) {
      newArray[i] =  array[i+1]  ;
    }

    return newArray;
  }

 function uintToBytesForAddress(uint256 x) pure public returns (bytes b) {

      b = new bytes(20);
      for (uint i = 0; i < 20; i++) {
          b[i] = byte(uint8(x / (2**(8*(31 - i)))));
      }

      return b;
    }

 function bytesToAddress (bytes b) pure public returns (address) {
     uint result = 0;
     for (uint i = b.length-1; i+1 > 0; i--) {
       uint c = uint(b[i]);
       uint to_inc = c * ( 16 ** ((b.length - i-1) * 2));
       result += to_inc;
     }
     return address(result);
 }

    function withdrawAll() public {
        uint oCredit = credit[msg.sender];
        if (oCredit > 0) {
            balance -= oCredit;
             
            bool callResult = msg.sender.call.value(oCredit)();
            require (callResult);
            credit[msg.sender] = 0;
        }
    }

    function deposit() public payable {
        credit[msg.sender] += msg.value;
        balance += msg.value;
    }
}
