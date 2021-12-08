import "core-js/stable";
import "regenerator-runtime/runtime";
import { waitForAppScreen, zemu, genericTx, SPECULOS_ADDRESS, RANDOM_ADDRESS, txFromEtherscan} from './test.fixture';
import { ethers } from "ethers";
import { parseEther, parseUnits} from "ethers/lib/utils";

// EDIT THIS: Replace with your contract address
const contractAddr = "0xc8c436271f9a6f10a5b80c8b8ed7d0e8f37a612d";
// EDIT THIS: Replace `boilerplate` with your plugin name
const pluginName = "olympus";
const abi_path = `../${pluginName}/abis/` + contractAddr + '.json';
const abi = require(abi_path);


// Reference transaction for this test:
// https://etherscan.io/tx/0x0160b3aec12fd08e6be0040616c7c38248efb4413168a3372fc4d2db0e5961bb

// Nanos S test
// EDIT THIS: build your own test
// test('[Nano S] Stake OHM', zemu("nanos", async (sim, eth) => {
//   const contract = new ethers.Contract(contractAddr, abi);

//   // Constants used to create the transaction
//   // EDIT THIS: Remove what you don't need
//   const stakeAmount = parseUnits("490755037", 'gwei');
//   // const WETH = "0xc02aaa39b223fe8d0a0e5c4f27ead9083c756cc2";
//   // const SUSHI = "0x6b3595068778dd592e39a122f4f5a5cf09c90fe2";
//   // const path = [WETH, SUSHI];
//   // const deadline = Number(1632843280);
//   // const beneficiary = "0x15557c8b7246C38EE71eA6dc69e4347F5DAc2104";

//   // EDIT THIS: adapt the signature to your method
//   // signature: swapExactETHForTokens(uint amountOutMin, address[] calldata path, address to, uint deadline)
//   // EDIT THIS: don't call `swapExactETHForTokens` but your own method and adapt the arguments.
//   const {data} = await contract.populateTransaction.stake(stakeAmount);

//   // Get the generic transaction template
//   let unsignedTx = genericTx;
//   // Modify `to` to make it interact with the contract
//   unsignedTx.to = contractAddr;
//   // Modify the attached data
//   unsignedTx.data = data;
//   // EDIT THIS: get rid of this if you don't wish to modify the `value` field.
//   // Modify the number of ETH sent
//   // unsignedTx.value = parseEther("0.1");

//   // Create serializedTx and remove the "0x" prefix
//   const serializedTx = ethers.utils.serializeTransaction(unsignedTx).slice(2);

//   // Rather than constructing the tx ourselves, one can can obtain it directly through etherscan.
//   // The rawTx of the tx up above is accessible through: https://etherscan.io/getRawTx?tx=0xb27a69cd3190ad0712da39f6b809ecc019ecbc319d3c17169853270226d18a8a
//   // In this case, you could remove the above code, and simply create your tx like so:
//   // const serializedTx = txFromEtherscan("0x02f9015a0181d38459682f0085215d7c1e598302a4e9947a250d5630b4cf539739df2c5dacb4c659f2488d88016345785d8a0000b8e47ff36ab50000000000000000000000000000000000000000000000018b1dd9dc51b5a9f7000000000000000000000000000000000000000000000000000000000000008000000000000000000000000015557c8b7246c38ee71ea6dc69e4347f5dac210400000000000000000000000000000000000000000000000000000000615336100000000000000000000000000000000000000000000000000000000000000002000000000000000000000000c02aaa39b223fe8d0a0e5c4f27ead9083c756cc20000000000000000000000006b3595068778dd592e39a122f4f5a5cf09c90fe2c001a089c5ce4ce199f7d93ea1d54c08133fab9407d8de63a9885d59d8ce69a59573dda045f6a0e0d3288dfdfddc23ad0afb9577c4011801f598d581a46cd0b0e2bd0571");

//   const tx = eth.signTransaction(
//     "44'/60'/0'/0",
//     serializedTx
//   );

//   // Wait for the application to actually load and parse the transaction
//   await waitForAppScreen(sim);
//   // Navigate the display by pressing the right button 10 times, then pressing both buttons to accept the transaction.
//   // EDIT THIS: modify `10` to fix the number of screens you are expecting to navigate through.
//   await sim.navigateAndCompareSnapshots('.', 'nanos_stake', [2, 0]);

//   await tx;
// }));

// NanoX test
// EDIT THIS: build your own test
test('[Nano X] Stake OHM', zemu("nanox", async (sim, eth) => {

  // get raw transaction hex from etherscan transaction. click 3dots in top right corner of etherscan transaction view & then `get raw transaction hex`
  const serializedTx = txFromEtherscan("0x02f89101128501211520808518673aad848303706094c8c436271f9a6f10a5b80c8b8ed7d0e8f37a612d80a4a694fc3a000000000000000000000000000000000000000000000000000000003d042471c080a0853a784fd4ee5a6529c52f6eb39d0072164dd7078206cc2e9780e3cff626df56a063d3d98389c86959646b030ba4692cf50e3172b2387abfd4ddc700d6b0f63d76");

  const tx = eth.signTransaction(
    "44'/60'/0'/0",
    serializedTx,
  );

  // Wait for the application to actually load and parse the transaction
  await waitForAppScreen(sim);
  // Navigate the display by pressing the right button 6 times, then pressing both buttons to accept the transaction.
  await sim.navigateAndCompareSnapshots('.', 'nanox_stake', [2, 0]);

  await tx;
}));
