import logo from './logo.svg';
import './App.css';
import styled from 'styled-components';

// import fetch from "node-fetch";
import { Graph } from "graphlib";
import { useEffect, useState } from 'react';

 

const g = new Graph({ directed: false, compound: false, multigraph: false });
const m = new Map();





// (value, key) for some reason.

const Node = styled.div`
  width: 1em;
  height: 1em;
  border-radius: 1em;
  background-color: white;
`;

function App() {
  const [overview, setOverview] = useState({});
  const [reports, setReports] = useState({});
  useEffect(()=> {
    fetch("MP0_results/overview.json").then(res => res.json()).then(data => setOverview(data));
  }, [])
  useEffect(()=>{
    const f = async () =>{
      m.clear();
      for (const a in overview['submission_ids_to_comparison_file_name']) {
        for (const b in overview['submission_ids_to_comparison_file_name'][a]) {
          m.set([a, b], overview['submission_ids_to_comparison_file_name'][a][b]);
        }
      }
      const filenames = [...m.values()];
      setReports((await Promise.all(filenames.map(async filename => await fetch(`MP0_results/${filename}`).then(res => res.json())))).map((r, i) => [filenames[i], r]));
      m.forEach((filename, [a, b]) => g.setEdge(a, b, filename));
    }
    f();
  },[overview]);
  useEffect(()=>{
    let M = [];
    for (let i = 0; i < g.nodeCount(); i++) {
      M.push(new Array(g.nodeCount()));
      for (let j = 0; j < g.nodeCount(); j++) {
        M[i][j] = 2.0;
      }
    }
    const Kc = (G, k) => {
      let S = new Set();
      S.add(g.nodes()[0]);
      for (let i = 2; i < k; i++) {
        
      }
    }
  },[reports])
  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Edit <code>src/App.js</code> and save to reload.
        </p>
        {g.edgeCount()}
        {g.nodes().map((n)=><Node/>)}
      </header>
    </div>
  );
}

export default App;
