import fetch from "node-fetch";
import {Graph} from "graphlib";

const overview = await fetch("http://localhost:8080/MP0_results/overview.json").then(res=>res.json());

const g = new Graph({ directed: false, compound: false, multigraph: false });
const m = new Map();

for (const a in overview['submission_ids_to_comparison_file_name']) {
    for (const b in overview['submission_ids_to_comparison_file_name'][a]) {
        m.set([a, b], overview['submission_ids_to_comparison_file_name'][a][b]);
    }
}

const filenames = [...m.values()];
const reports = (await Promise.all(filenames.map(async filename => await fetch(`http://localhost:8080/MP0_results/${filename}`).then(res => res.json())))).map((r, i) => [filenames[i], r]);

// (value, key) for some reason.
m.forEach((filename, [a, b]) => console.log(a, b, filename));

